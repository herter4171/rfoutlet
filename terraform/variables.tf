###############################################################################
# INGRESS PORTS
###############################################################################

variable port-ssh {
  type        = string
  default     = 22
  description = "SSH port"
}
variable port-redis {
  type        = string
  default     = 6379
  description = "Redis server port"
}

###############################################################################
# ADRESSES AND MISC
###############################################################################

variable local-ip {
  type        = string
  default     = "75.3.244.182"
  description = "IP of network Raspberry Pi is on"
}

variable vpc-id {
    type        = string
    default     = "vpc-5c547d3b"
    description = "VPC to be used throughout"
}

variable eip-id {
    type        = string
    default     = "eipalloc-0438e7c8248878f3a"
    description = "Elastic IP ID"
}