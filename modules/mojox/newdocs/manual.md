
@manpage The mojox module

#The mojox module

#### View layout

View layout occurs just before rendering and is a two pass process.

The first pass is a measuring pass. The view hierarchy is visited in 'bottom up' order and each view's [[View.OnMeasure|OnMeasure]] method is called. The returned size has the size of the view's border added to it (border size is determined by the view's [[View.Style|Style]]) and the result is stored as the view's [[View.MeasuredSize|MeasuredSize]]. Since the measuring process is bottom up, views with child views can safely use the MeasuredSize property of any child views when measuring themselves during OnMeasure.

The second pass is a layout pass. The view hierarchy is again visited, this time in 'top down' order, and each view's [[View.OnLayout|OnLayout]] method is called. Views that contain child view should 'layout' their child views by setting the [[View.Frame|Frame]] property of any child views. Again, views can use the MeasuredSize property of any child views calculated in the measuring pass during OnLayout.
