# AVOE gamepad support plugins


## Implementation
`controller.h`, located in lib defines a class implmentation for generic controller support that can get raw controller data. It also defines a generic data structure for storing parsed controller data. You must write a "translater" function that converts raw data captured from the generic driver `controller_generic_raw` into to a `controller_generic_profile` type which can be used by a frontend.


 
