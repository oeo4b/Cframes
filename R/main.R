##
#
# Bootstrapping methods for R scripting
#
##

## Globals
path <<- getwd()
maxchar <<- 100000

# Get command line args
c <- commandArgs(trailingOnly = T)
controller <<- c[1]
action <<- c[2]

## Check for valid paths
controllers <- dir("app/controllers/")
models <- dir("app/models/")
views <- dir("app/views/")

controllerbool <<- FALSE
for(i in controllers) {
  if(i==paste(controller, "_controller.R", sep="")) {
    controllerbool <<- TRUE
  }
}

# Lib functions
camelcase <- function(x) {
  case <- paste(toupper(substr(x, 1, 1)), 
  ifelse(nchar(x)>1, substr(x, 2, nchar(x)), ""),
  "Controller", sep="")
  return(case)
}

## Main function
main <- function() {
  # Include the controller
  source("R/controller.R")
  source("app/controllers/app_controller.R")
  source(paste("app/controllers/", controller, "_controller.R", sep=""))

  # Valid controller/action args -- start app
  object <- new(camelcase(controller))
  called <- call(action, object)

  # 'this' is the object that can be called from the view templates
  this <- eval(called)

  # Send evaluated object to the view
  source("R/view.R") 
  template <- new("view")
  template@controller <- controller
  template@action <- action
  rendered <- render(template)

  # Evaluate and render to tmp file
  eval(parse(text=rendered))
}

# If false return error
if(controllerbool) {
  main()
}
if(!controllerbool) {
  # Invalid path return error
  cat("Error: No controller script present\n")
}