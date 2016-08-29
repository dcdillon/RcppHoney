inlineCxxPlugin <- Rcpp:::Rcpp.plugin.maker(libs =
                       if (Sys.info()[['sysname']] != "SunOS") "-Wl,-S" else "")
