# Base class for all controllers
setClass("Controller",
  representation(id="character", other="numeric")
)

setGeneric("index",
  function(controller, ...) 
    standardGeneric("index")
)
setGeneric("create",
  function(controller, ...) 
    standardGeneric("create")
)
setGeneric("read",
  function(controller, ...) 
    standardGeneric("read")
)
setGeneric("update",
  function(controller, ...) 
    standardGeneric("update")
)
setGeneric("destroy",
  function(controller, ...) 
    standardGeneric("destroy")
)