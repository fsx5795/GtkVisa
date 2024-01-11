#include "window.h"
#include "fpc.h"
int main(int argc, char *argv[])
{
	asyncQueue = g_async_queue_new();
	struct Xrange xrange;
	init_fpc(&xrange.min, &xrange.max, show_data);
	GtkApplication *app = gtk_application_new("nook.inc", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(on_activate), &xrange);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	clear_fpc();
	return status;
/*
	//中心频率步长
	status = viPrintf(vi, "FREQ:CENT:STEP:LINK OFF\n");
	if (!result_analy(status))
		goto joinThread;
	status = viPrintf(vi, "FREQ:CENT:STEP %s\n", "50MHZ");
	if (!result_analy(status))
		goto joinThread;
	//轨迹模式必须置于打开轨迹2上方，原因未知
	status = viPrintf(vi, "DISP:TRAC:MODE %s\n", "MINH");
	if (!result_analy(status))
		goto joinThread;
	//打开轨迹2
	status = viPrintf(vi, "DISP:TRAC2 %s\n", "OFF");
	if (!result_analy(status))
		goto joinThread;
	joinThread:
	g_thread_join(thr);
	return 0;
	*/
}