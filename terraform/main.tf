provider "aws" {
  profile    = "default"
  region     = "us-west-1"
}

resource "aws_instance" "front_end_server" {
  
  // Use the AMI from Packer
  ami           = "ami-0d3ea0b56fa289e40"

  // Want to be in the free tier
  instance_type = "t2.micro"
  
  // Want ingress from SSH, Redis and egress to open net
  vpc_security_group_ids = ["${aws_security_group.plant_sg.id}"]
  key_name = "plant_fe"

  connection {
    host = coalesce(self.public_ip, self.private_ip)
    user = "ec2-user"
    private_key = file("${path.module}/../plant_fe")
  }

  provisioner "remote-exec" {
    script = "${path.module}/launch_fe.sh"
  }

  // Name for display in console
  tags = {
      Name = "Plant-Monitor-Frontend"
  }
}

// Want a fixed address if instance has to be reprovisioned
resource "aws_eip" "front_end_eip" {
  instance = "${aws_instance.front_end_server.id}"
  vpc = true
}