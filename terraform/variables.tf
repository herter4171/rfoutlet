###############################################################################
# INGRESS PORTS
###############################################################################

variable port-ssh {
  default     = 22
  description = "SSH port"
}
variable port-redis {
  default     = 6379
  description = "Redis server port"
}

variable port-flask {
  default = 5000
  description = "Flask listening port"
}

###############################################################################
# ADRESSES AND MISC
###############################################################################

variable local-ip {
  default     = "75.3.244.182"
  description = "IP of network Raspberry Pi is on"
}