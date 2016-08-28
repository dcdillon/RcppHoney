inlineCxxPlugin <- ifelse(Sys.info()[['sysname']] != "SunOS",
                          Rcpp:::Rcpp.plugin.maker(
                              libs = "-Wl,-S"
                          ),
                          Rcpp:::Rcpp.plugin.maker(
                              libs = ""
                          ))
