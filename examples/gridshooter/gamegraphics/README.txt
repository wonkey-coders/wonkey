#GameGraphics

A collection of game related drawing objects.

- Sprite: A basic sprite system featuring spritesheet loading, easy texture filtering, animation clips (series of frames played back sequentially) and playback framerate.

- Background: An "infinite background" that takes a single texture and tiles it in a way that respects the Canvas translation, as long as you provide a camera Rect containing the camera corners (corrected for parallax, if necessary)

Roadmap: Add Tilemap (will use a similar system as the Background object), "9-patches", Textbox.
