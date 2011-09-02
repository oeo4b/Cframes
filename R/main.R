##
#
# Bootstrapping methods for R scripting
#
##

# Globals
path <<- getwd()

# Get command line args
c <- commandArgs(trailingOnly = T)
controller <<- c[1]
action <<- c[2]

# Check for valid paths
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

# Main function
main <- function() {
  # Valid controller/action args -- start app
  
  
}

# If false return 
if(check==2) {
  main()
}
if(check!=2) {
  # Invalid path return error
  cat("Error\n")
}