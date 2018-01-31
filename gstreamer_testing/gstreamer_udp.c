#include <gst/gst.h>

int main(int argc, char *argv[]) {
	GstElement *pipeline, *source, *sink, *appsrc, *conv, *videoenc, *videosink,
			*payloader, *udpsink;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	gst_init(&argc, &argv);

	/* Create the elements */
	source = gst_element_factory_make("udpsrc", "source1");
	sink = gst_element_factory_make("udpsink", "udpsink");
	//sink = gst_element_factory_make("autovideosink", "sink");
	appsrc = gst_element_factory_make("appsrc", "source2");
	conv = gst_element_factory_make("videoconvert", "conv");
//	videoenc = gst_element_factory_make("avenc_mpeg4", "ffenc_mpeg4");
	videosink = gst_element_factory_make("xvimagesink", "videosink");
	payloader = gst_element_factory_make("rtpmp4vpay", "rtpmp4vpay");

	g_object_set(G_OBJECT(sink), "host", "10.5.5.9", "port", 8554, NULL);

	g_object_set(G_OBJECT(payloader), "config-interval", 60, NULL);
	udpsink = gst_element_factory_make("udpsink", "udpsink");
	g_object_set(G_OBJECT(udpsink), "host", "10.5.5.4", "port", 8554, NULL);

    g_object_set (G_OBJECT (appsrc), "caps",
            gst_caps_new_simple ("video/x-raw",
                "format", G_TYPE_STRING, "RGB16",
                "width", G_TYPE_INT, 384,
                "height", G_TYPE_INT, 288,
                "pixel-aspect-ratio", GST_TYPE_FRACTION, 1, 1,
                "framerate", GST_TYPE_FRACTION, 0, 1,
NULL), NULL);



	/* Create the empty pipeline */
	pipeline = gst_pipeline_new("test-pipeline");

	if (!pipeline || !source || !sink || !appsrc || !conv || !payloader
			|| !videosink) { //
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	/* Build the pipeline */
/*	gst_bin_add_many(GST_BIN(pipeline), source, sink, conv, payloader,
			videosink, NULL);
	if (gst_element_link(source, sink) != TRUE) {
		g_printerr("Elements could not be linked.\n");
		gst_object_unref(pipeline);
		return -1;
	}*/
    gst_bin_add_many (GST_BIN (pipeline), source, appsrc, conv, payloader, udpsink, NULL);
    gst_element_link_many (appsrc, source, conv, payloader, udpsink, NULL);

	g_object_set(source, "uri", "udp://10.5.5.9:8554", NULL);

	/* Modify the source's properties */
	//g_object_set (source, "pattern", 0, NULL);
	/* Start playing */
	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(pipeline);
		return -1;
	}else{
		g_print("hi");
	}

	/* Wait until error or EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
			GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* Parse message */
	if (msg != NULL) {
		GError *err;
		gchar *debug_info;

		switch (GST_MESSAGE_TYPE(msg)) {
		case GST_MESSAGE_ERROR:
			gst_message_parse_error(msg, &err, &debug_info);
			g_printerr("Error received from element %s: %s\n",
					GST_OBJECT_NAME(msg->src), err->message);
			g_printerr("Debugging information: %s\n",
					debug_info ? debug_info : "none");
			g_clear_error(&err);
			g_free(debug_info);
			break;
		case GST_MESSAGE_EOS:
			g_print("End-Of-Stream reached.\n");
			break;
		default:
			/* We should not reach here because we only asked for ERRORs and EOS */
			g_printerr("Unexpected message received.\n");
			break;
		}
		gst_message_unref(msg);
	}

	/* Free resources */
	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
	return 0;
}
