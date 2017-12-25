// from: https://gstreamer.freedesktop.org/documentation/tutorials/basic/streaming.html
// dnf install gstreamer1-devel gstreamer1-plugins-base-tools gstreamer1-devel-docs gstreamer1-plugins-base-devel gstreamer1-plugins-base-devel-docs gstreamer1-plugins-good gstreamer1-plugins-good-extras gstreamer1-plugins-ugly gstreamer1-plugins-ugly-devel-docs  gstreamer1-plugins-bad-free gstreamer1-plugins-bad-free-devel gstreamer1-plugins-bad-free-extras


#include <gst/gst.h>
#include <string.h>
#include <glib.h>

/* what chrisy wants

- video von python in den gstreamer laden


*/

/*	UDP_IP = "10.5.5.9"
	UDP_PORT = 8554
	KEEP_ALIVE_PERIOD = 2500
	KEEP_ALIVE_CMD = 2
*/

typedef struct _CustomData {
  gboolean is_live;
  GstElement *pipeline;
  GMainLoop *loop;
} CustomData;

static void cb_message (GstBus *bus, GstMessage *msg, CustomData *data) {

  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_ERROR: {
      GError *err;
      gchar *debug;

      gst_message_parse_error (msg, &err, &debug);
      g_print ("Error: %s\n", err->message);
      g_error_free (err);
      g_free (debug);

      gst_element_set_state (data->pipeline, GST_STATE_READY);
      g_main_loop_quit (data->loop);
      break;
    }
    case GST_MESSAGE_EOS:
      /* end-of-stream */
      gst_element_set_state (data->pipeline, GST_STATE_READY);
      g_main_loop_quit (data->loop);
      break;
    case GST_MESSAGE_BUFFERING: {
      // stream is live, we do not care about buffering.
      if (data->is_live) break;
      break;
    }
    case GST_MESSAGE_CLOCK_LOST:
      /* Get a new clock */
      gst_element_set_state (data->pipeline, GST_STATE_PAUSED);
      gst_element_set_state (data->pipeline, GST_STATE_PLAYING);
      break;
    default:
      /* Unhandled message */
      break;
    }
}

int main(int argc, char *argv[]) {
  GstElement *pipeline;
  GstBus *bus;
  GstStateChangeReturn ret;
  GMainLoop *main_loop;
  CustomData data;
GError *err = NULL;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Initialize our data structure */
  memset (&data, 0, sizeof (data));

  /* Build the pipeline */
  pipeline = gst_parse_launch ("playbin udpsrc port=8554", &err);
 if (!pipeline) {
    g_print ("Parse error: %s\n", err->message);
    exit (1);
  }
	if(err!=NULL){
    g_printerr ("Aye, some probs\n");
}else{
    g_printerr ("Aye, ok\n");
}
  bus = gst_element_get_bus (pipeline);

  /* Start playing */

 ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
 if (ret == GST_STATE_CHANGE_FAILURE) {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    gst_object_unref (pipeline);
    return -1;
  } else if (ret == GST_STATE_CHANGE_NO_PREROLL) {
    g_printerr ("lslsls\n");
    data.is_live = TRUE;
  }

  main_loop = g_main_loop_new (NULL, FALSE);
g_printerr ("Main Loop\n");
  data.loop = main_loop;
g_printerr ("data Loop\n");
  data.pipeline = pipeline;
g_printerr ("pipeline Loop\n");

  gst_bus_add_signal_watch (bus);
g_printerr ("1 Loop\n");
  g_signal_connect (bus, "message", G_CALLBACK (cb_message), &data);
g_printerr ("2 Loop\n");
  g_main_loop_run (main_loop);
g_printerr ("3 Loop\n");
  /* Free resources */
g_printerr ("free\n");
  g_main_loop_unref (main_loop);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0;
}
