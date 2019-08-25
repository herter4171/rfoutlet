
resource "aws_security_group" "plant-sg" {
    name = "plant-sg"
    description = "Set ingress/egress for front-end server"
    vpc_id = var.vpc-id

    // Incoming SSH from local IP
    ingress {
        from_port   = var.port-ssh
        to_port     = var.port-ssh
        protocol    = "tcp"
        cidr_blocks = ["${var.local-ip}/32"]
    }

    // Incoming Redis client from local IP
    ingress {
        from_port   = var.port-redis
        to_port     = var.port-redis
        protocol    = "tcp"
        cidr_blocks = ["${var.local-ip}/32"]
    }

    // Outgoing to open net
    egress {
        from_port   = 0
        to_port     = 0
        protocol    = "-1"
        cidr_blocks = ["0.0.0.0/0"]        
    }
}