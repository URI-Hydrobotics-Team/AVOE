# Visual Point to Point Navigation (VPPN) mission control module for Tardigrade


The VPPN scheme is simple: `mc_vppn` manages a queue of `mission_vppn_t` objects which contain a few parameters including a `keyword` string which indicates the object specified by the `mission_vppn_t` frame. `mc_vppn` is always listening on a socket connection where the computer vision (CV) stack is publishing the current object being reckognized (`keyword`) and its x and y pixel offset from the center of the camera's view port. `mc_vppn` will interface with a controller to drive tardigrade torwads the object. Two types of `mission_vppn_t` objects exist, "main" objects and dead reckon "dr" objects.



## Operating Procedure
The `refresh()` method is called continously in a loop. This method manages all control and waits for other signals to be sent in the form of variable changes which are envoked via the other methods 'start()', 'resume()', etc.  Once `start()` is called, a scanning procedure will start and the keyword in the first main mission object will be searched for. Once found the mode will be switched to 1 or "running". In mode 1 the AUV will attempt to maintain course, correcting when needed, following the detected object. Once the object is lost for a certain interval, a decision needs to be made as to switch to dead reckon mode or not. When `dead_reckon` is true, global mode 1 will be kept ad the AUV follows the path it was on while doing periodic sweeps at a set speed (defined in the mission dead reckon object). It is still unclear as to which conditions we should bumb the dead reckon and main mission object pointers.
