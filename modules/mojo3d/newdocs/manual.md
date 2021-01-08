
@manpage The mojo3d module

# The mojo3d module

Mojo3d is a simple 3d rendering engine.

@#### The mojo3d graphics system

Mojo3d is a scene graph based rendering engine. Currently, only a singleton scene is supported. This can be retrieved using the [[Scene.GetCurrent]] function.

The base class of all scene nodes is the [[Entity]] class. Subclasses of entity include [[Camera]], [[Light]], [[Model]] and [[Sprite]]. Entities can be arranged in hierarchies using the [[Entity.Parent]] property.

A number of helper entity [[EntityEXT|extension]] properties and methods are also available for working with entities.

@#### The mojo3d-loaders module

Mojo3d includes a native gltf2 loader, which is used by default by the [[Mesh.Load]] and [[Model.Load]] methods.

To load other 3d file formats, you can import the mojo3d-loaders module simply adding `#Import "<mojo3d-loaders>"` to your project. Note that this will increase the size of your final application somewhat.


