# timelinefx.monkey2

TimelineFX is a particle effects module for Monkey 2 programming language (https://github.com/blitz-research/monkey2) that also includes some extra code for handling collisions.

You can use the TimeineFX Editor from here: (http://www.rigzsoft.co.uk) to design your effects and play them back in realtime in Monkey 2. There is an overview of the editor
here (http://www.rigzsoft.co.uk/timelinefx-help/) which will also give you an idea about about the particles work.

###Installation from git
Clone into your Monkey2 modules folder under timelinefx. In a command prompt/terminal cd to monkey2/bin and type:

Windows:
`mx2cc_windows makemods timelinefx`

Mac:
`./mx2cc_macos makemods timelinefx`

Linux:
`./mx2cc_linux makemods timelinefx`

To compile in release use the -config=release option like so:
`mx2cc_windows makemods -config=release timelinefx`

###Installation from Ted2
You can also install TimelineFX from the module manager in Ted2 (the IDE of Monkey 2), You'll find it under Build > Module Manager.

##Here’s an overview of some of the commands you’ll be using the most in TimelineFX.

TimelineFX is very Object Orientated so most of the commands are accessed through the objects you create. The main object in TimelineFX you will use is *tlParticleManager*. You need to know how to create one, how to update it, and how to render the effects and particles it is managing. You also need to tell it the size of the screen you are rendering to.
Here’s how you create one:

	MyParticleManager:tlParticleManager = CreateParticleManager()

Pretty straightforward. There is a parameter you can pass to the create command which is Particles:int. This defines the maximum amount of particles that this particle manager can update and render at any one time. The default value is 5000 which should be more then enough for most games, probably even too much!
You can create as many particle managers as you need. This can be handy if you want to draw certain particles in front or behind your other drawing routines. For example you could have:

	BackGroundParticles:tlParticleManager=CreateParticleManager(250)
	MidGroundParticles:tlParticleManager=CreateParticleManager(2500)
	ForeGroundParticles:tlParticleManager=CreateParticleManager(500)

So with a particle manager defined you now have a number of important commands you can access through the particle manager. The first should be called right after you have created the particle manager:

	MyParticleManager.SetScreenSize(GraphicsWidth(),GraphicsHeight())

This command must be set for each particle manager you create so that they know where to draw particles. TimelineFX uses an entity system where the origin of those entities can be set anywhere. By default if you draw an effect at 0,0 coordinates then the effect will be drawn at the center of the screen. If you plan on being able to zoom in and out then you’ll be wanting this kind of a set up. If you don’t care for any of that though then maybe you just want effects to be drawn at screen coordinates ie., an effect drawn at 0,0 will be rendered in the top-left of the screen. To ensure this happens you need to use the SetOrigin command like so:

	MyParticleManager.SetOrigin(Width/2, Height/2)

_Note that this assumes you call the command within a Monkey2 Window class where the Width and Height Properties are readily available_

So with that you can now draw effects at screen coordinates. If your game scrolls about a world then SetOrigin will be what you need to use to keep the particle manager in sync with your game camera or which ever method you use.

So you know how to create and initialise a particle manager, now you need to know how to update and render the particle effects. It’s quite simple, you need the Update and Render commands:

	MyParticleManager.Update()

	MyParticleManager.DrawParticles()

If you’re using some kind of timing code with tweening then you’ll need to put the Update command in with your logic updates and the Render command outside in your main loop and pass it the tween value like so:

	MyParticleManager.DrawParticles(tween)

Of course, a particle manager is not much use without any particles to manage. To add an effect to it you need a new object: the tlEffectsLibrary. An effects library is a bunch of effects you would have created with the TimelineFX Editor. So to create and load a library you can use the LoadEffects command like so:

	MyEffectsLibrary:tlEffectsLibrary=LoadEffects("effect.eff")

This will load the effects, now we need to retrieve the effect we want to use. For this, a quick introduction to a new object: tlEffect and a the command GetEffect.

	MyEffect:tlEffect=MyEffectsLibrary.GetEffect("My Effect")

It’s important to note that the effect we get from the library should be treated as a template effect that we use to copy before adding the copy to the particle manager. The particle manager will be making changes to certain values within the effect such as age, current frame etc., so we don’t want it doing that to the same effect. So to make a copy we can use:

	CopyEffect(MyEffect)

Now, to add to the particle manager with the command AddEffect we could simply do this:

	MyParticleManager.AddEffect(CopyEffect(MyEffect))

That will get the job done. However, in most situations you will probably want to position the effect using SetPostion. So first you’ll need a temporary variable:

	Local TempEffect:tlEffect=CopyEffect(MyEffect)
	TempEffect.SetPosition(100, 250)
	MyParticleManager.AddEffect(TempEffect)

The TempEffect can now be discarded as it is now managed by the particle manager. Now that the Particle manager has something to work with you can start seeing some effects on screen.
So those are the main commands that you need to get your effects up and running in your game. In the Vaders mini game that comes with the module there are very few other commands it uses which isn’t listed here. 2 of those are:

	MyParticleManager.IdleTimeLimit = 10

All this does is tell the particle manager how long it should wait (in frame updates) before removing effects it manages that no longer have particles. You may wonder what the point of it is, but with some effects you might have points where the effect is not spawning anything for a while but it will in a short while, for example: intermittent lightening effects. So you can use this to set the idle time to an amount where you know effects will only be deleted when you know for sure they have actually finished.
The other command I mentioned is a basic clean up command to remove all effects and particles from the manager:

	MyParticleManager.ClearAll()

That will instantly clear out all of the effects and particles currently being rendered so quite handy if its the end of the game and you want to switch back to the title screen or something.

Take a look at the samples folder for more examples, including how to use the collision system that comes with TimelineFX.