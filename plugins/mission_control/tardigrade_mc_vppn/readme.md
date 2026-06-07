# Visual Point to Point Navigation (VPPN) mission control module for Tardigrade


The VPPN scheme is simple `mc_vppn` manages a queue of `mission_vppn_t` objects which contain a few parameters including a `keyword` string which indicates the object specified by the `mission_vppn_t` frame. `mc_vppn` is always listening on a socket connection where the computer vision (CV) stack is publishing the current object being reckognized (`keyword`) and its x and y pixel offset from the center of the camera's view port. `mc_vppn` will interface with a controller to drive tardigrade torwads the object. Two types of `mission_vppn_t` objects exist, "main" objects and dead reckon "dr" objects.
