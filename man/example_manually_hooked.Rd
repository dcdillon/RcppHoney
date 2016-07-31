\name{example_manually_hooked}
\alias{example_manually_hooked}
\title{
example_manually_hooked
}
\description{
Simple demonstration of RcppHoney functionality.
}
\usage{
example_manually_hooked()
}
\value{
A numeric vector.
}
\author{
Daniel C. Dillon
}
\examples{
library(RcppHoney)
v <- 1:5
all.equal(example_manually_hooked(), 42 + (v + v + 2.0) + v + v + log(v) - v - v + sqrt(v) + -v + (v + 1.0) + 42)
}
