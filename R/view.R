setClass("view",
  representation(controller="character", action="character")
)

setGeneric("render",
  function(template, ...) 
    standardGeneric("render")
)

setMethod("render", "view",
  function(template, ...) {
    # Get view templates
    maxchars <- 100000
    layout <- readChar(file(paste("app/views/layouts/", template@controller, ".html.R", sep="")), nchars=maxchars)
    top <- readChar(file(paste("app/views/", template@controller, "/", template@action, ".html.R", sep="")), nchars=maxchars)

    # Render top/layout 
    top <- escape(top)
    layout <- escape(layout)

    # Render the top on the layout
    i <- 1
    while(i<(nchar(layout)-3)) {
      if(substr(layout, i, i+4)=="yield") {
        layout <- paste(substr(layout, 1, i-1), top, substr(layout, i+5, nchar(layout)), sep="")
      }
      i <- i+1
    }

    return(layout)
  }
)


escape <- function(top) {
    i <- 1 
    while(i<(nchar(top)-1)) {
      strt <- substr(top, i, i+2)
      if(strt=="<?R") {
        top <- paste(substr(top, 1, i-1), "\");", substr(top, i+3, nchar(top)), sep="")
      }
      strt <- substr(top, i, i+1)
      if(strt=="?>") {
        top <- paste(substr(top, 1, i-1), "cat(\"", substr(top, i+2, nchar(top)), sep="")
      }
    i <- i+1
    }
  top <- paste("cat(\"", top, "\");", sep="")
  return(top)
}
