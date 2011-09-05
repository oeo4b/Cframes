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

check <- 0
for(i in controllers) {
  if(i==paste(controller, "_controller.R", sep="")) {
    check <- check+1
  }
}

for(i in models) {
  if(i==paste(controller, ".R", sep="")) {
    check <- check+1
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
  # Include the controller/model
  source("R/model.R")
  source(paste("app/models/", controller, ".R", sep=""))
  source("R/controller.R")
  source("app/controllers/app_controller.R")
  source(paste("app/controllers/", controller, "_controller.R", sep=""))

  # Valid controller/action args -- start app
  object <- new(camelcase(controller))
  called <- call(action, object)
  data <- eval(called)

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
if(check==2) {
  main()
}
if(check!=2) {
  # Invalid path return error
  cat("Error\n")
}