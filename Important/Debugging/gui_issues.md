### Gstreamer
Frage: kann gstreamer auch dateien streamen, die nur für genau die sekunde verfügbar sind? 
-> beim example wird ein bsp video aus dem internet verwendet - video ist kein lifestream

Antwort: Live streams cannot be paused, so they behave in PAUSED state as if they were in the PLAYING state. Setting live streams to PAUSED succeeds, but returns GST_STATE_CHANGE_NO_PREROLL, instead of GST_STATE_CHANGE_SUCCESS to indicate that this is a live stream. We are receiving the NO_PREROLL return code even though we are trying to set the pipeline to PLAYING, because state changes happen progressively (from NULL to READY, to PAUSED and then to PLAYING).

We care about live streams because we want to disable buffering for them, so we take note of the result of gst_element_set_state() in the is_live variable.
