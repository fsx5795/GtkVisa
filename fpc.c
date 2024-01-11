#include <gtk/gtk.h>
#include "visa.h"
#include "fpc.h"

static minX, maxX;
static bool exitThread = false;
GThread *thr;
static ViSession sesn, vi;
static bool result_analy(ViStatus status)
{
	switch (status) {
		case VI_SUCCESS:
			return true;
		case VI_SUCCESS_DEV_NPRESENT:
			break;
		case VI_WARN_CONFIG_NLOADED:
			break;
		case VI_ERROR_ALLOC:
			break;
		case VI_ERROR_INTF_NUM_NCONFIG:
			break;
		case VI_ERROR_INV_ACC_MODE:
			break;
		case VI_ERROR_INV_RSRC_NAME:
			break;
		case VI_ERROR_INV_SESSION:
			break;
		case VI_ERROR_RSRC_BUSY:
			break;
		case VI_ERROR_RSRC_LOCKED:
			break;
		case VI_ERROR_RSRC_NFOUND:
			break;
		case VI_ERROR_TMO:
			break;
	}
	return false;
}

static void show_data(gpointer data)
{
	//void (*func)(struct Point*, int) = data;
	if (minX == 0 && maxX == 0)
		return;
	char *str = malloc(80000);
	if (str == NULL)
		return;
	while (!exitThread) {
		memset(str, '\0', 80000);
		ViStatus status = viQueryf(vi, "TRACe:DATA?\n", "%s", str);
		GArray *array = g_array_new(false, false, sizeof(double));
		if (result_analy(status) && str != NULL) {
			char *token = strtok(str, ",");
			while (token != NULL) {
				double v = atof(token);
				g_array_append_val(array, v);
				token = strtok(NULL, ",");
			}
			struct Point *pt = malloc(sizeof(struct Point) * array->len);
			if (pt != NULL) {
				for (int i = 0; i < array->len; ++i) {
					pt[i].x = i * (maxX - minX) / array->len;
					pt[i].y = g_array_index(array, double, i);
					printf("%d, %f\n", i, pt[i].y);
				}
				g_async_queue_lock(asyncQueue);
				struct Points *ps = malloc(sizeof(struct Points));
				ps->pt = pt;
				ps->leng = array->len;
				g_async_queue_push_unlocked(asyncQueue, ps);
				g_async_queue_unlock(asyncQueue);
				//func(pt, array->len);
			}
			g_array_free(array, true);
		} else {
			break;
		}
		g_usleep(1000 * 1000);
	}
	free(str);
	return;
}

bool init_fpc(double *min, double *max, void (*func)(struct Point*, int))
{
	ViStatus status = viOpenDefaultRM(&sesn);
	if (!result_analy(status))
		return false;
	status = viOpen(sesn, "TCPIP0::192.168.0.251", VI_NULL, 0, &vi);
	if (!result_analy(status))
		return false;
	double data = 0.0;
	status = viQueryf(vi, "freq:start?\n", "%lf", (char*)&data);
	if (!result_analy(status))
		return false;
	minX = *min = data / 1e6;
	printf("%f MHz\n", data / 1e6);
	status = viQueryf(vi, "freq:stop?\n", "%lf", (char*)&data);
	if (!result_analy(status))
		return false;
	maxX = *max = data / 1e6;
	printf("%f MHz\n", data / 1e6);
	status = viQueryf(vi, "DISP:TRAC:Y:RLEV?\n", "%lf", (char*)&data);
	if (!result_analy(status))
		return false;
	printf("%f dBm\n", data);
	thr = g_thread_new(NULL, (GThreadFunc)show_data, func);
	return true;
}

void clear_fpc(void)
{
	if (thr != NULL) {
		exitThread = true;
		g_thread_join(thr);
	}
	viClose(vi);
	viClose(sesn);
	return;
}
