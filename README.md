# SimpleTalk
A simple "chat"-like facility that enables someone at one terminal (or Xterm) to communicate with someone at another terminal. 

All four threads will share access to a list ADT:

- The keyboard input thread, on receipt of input, adds the input to the list of messages that need to be sent to the remote s-talk client.

- The UDP output thread will take each message off this list and send it over the network to the remote client.

- The UDP input thread, on receipt of input from the remote s-talk client, will put the message onto the list of messages that need to be printed to the local screen.

- The screen output thread will take each message off this list and output it to the screen.

```
./s-talk 6001 csil-cpu5 6000
```

```
./s-talk 6000 csil-cpu4 6001
```

