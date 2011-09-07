#  
# Class definitions for the index controller;
# This class should inherit the AppController class.
#
# Slots can be called via the object 'this' in the view (example: this@greeting);
# The representation function must define all the slots that need to be accessed
# in the view.
#

setClass("IndexController",
  contains = "AppController",
  representation=representation(
    greeting = "character"
  )
)

# Generics are set for some basic CRUD functions ( index, create, read, update, destroy)
# Any other generic function for a particular action needs to be explicitly set via this call:
#
# setGeneric("action",
#   function(controller, ...)
#     standardGeneric("index")
# )
#


#
# All method signatures must include the appropriate controller class.
# Each method should return the controller object -- they are not passed
# by reference.
#

setMethod("index", "IndexController",
  function(controller) {
    # Set method actions here
    controller@greeting = "Hello, world"
    return(controller)
  }
)

