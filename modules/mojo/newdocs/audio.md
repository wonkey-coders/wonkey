
@manpage Audio

### Audio

The [[Audio]] global contains a read only instance of an [[AudioDevice]] object which can be used to [[AudioDevice.PlayMusic|play music]].

A [[Sound]] object contains static audio data that can be play through [[Channel]] objects.

A sound object can be loaded from file using [[Sound.Load]] or constructed from an [[std::std.audio.AudoData|AudioData]] object.

There are several ways to play a sound:

* Using [[Sound.Play]] to play a sound object through a temporary channel object.

* Playing a sound through an existing channel using [[Channel.Play]].


#### Music

Music can be streamed from file using [[AudioDevice.PlayMusic|Audio.PlayMusic]].

Music must currently be in ogg format.





