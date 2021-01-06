
@manpage User input

To handle keyboard input, an app can either handle KeyEvent events by overriding the [[View.OnKeyEvent]] method, or poll the [[KeyboardDevice]] directly using the global [[Keyboard]] const.

To handle mouse input, an app can either handle MouseEvent events by overriding the [[View.OnMouseEvent]] method, or poll the [[MouseDevice]] directly using the global [[Mouse]] const.

To handle touch input, an app can poll the [[TouchDevice]] directly using the global [[Touch]] const.


