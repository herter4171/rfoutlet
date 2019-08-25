provider "aws" {
  profile    = "default"
  region     = "us-west-1"
}

resource "aws_instance" "front-end-server" {
  
  // Use the AMI from Packer
  ami           = "ami-0d3ea0b56fa289e40"

  // Want to be in the free tier
  instance_type = "t2.micro"
  
  // Want ingress from SSH, Redis and egress to open net
  vpc_security_group_ids = ["${aws_security_group.plant-sg.id}"]
  key_name = "plant_fe"

  // Name for display in console
  tags = {
      Name = "Plant-Monitor-Frontend"
  }
}

// Want a known, static IP for the remote
resource "aws_eip_association" "eip_assoc" {
  instance_id   = "${aws_instance.front-end-server.id}"
  allocation_id = var.eip-id
}