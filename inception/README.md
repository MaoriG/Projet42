*This project has been created as part of the 42 curriculum by mgobert.*

# Inception

## Description

**Inception** is a DevOps project from the 42 curriculum.  
The goal of this project is to design and deploy a secure and modular web infrastructure using **Docker** and **Docker Compose**.

The infrastructure hosts a **WordPress website** served over **HTTPS only**, backed by a **MariaDB database**, and exposed through an **NGINX web server**.  
Each service runs in its own dedicated container and communicates through a private Docker network, following best practices for security, isolation, and maintainability.

The project focuses on understanding containerization, service orchestration, networking, volumes, and environment-based configuration.

---

## Project Architecture

The stack consists of the following services:

- **NGINX**
  - Acts as a reverse proxy and web server
  - Handles HTTPS with TLS certificates
  - Only exposed container to the host

- **WordPress (PHP-FPM)**
  - Runs the WordPress application
  - Communicates with NGINX via FastCGI
  - Connects to MariaDB for data storage

- **MariaDB**
  - Relational database used by WordPress
  - Not exposed to the host
  - Accessible only from the Docker network

All containers are connected through a **custom Docker bridge network**.

---

## Instructions

### Prerequisites

- Linux virtual machine
- Docker
- Docker Compose
- Make

### Installation & Execution

1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd inception
Create a .env file at the root of the project and define the required environment variables:

env
Copier le code
DOMAIN_NAME=mgobert.42.fr
MYSQL_DATABASE=wordpress
MYSQL_USER=wp_user
MYSQL_PASSWORD=strong_password
MYSQL_ROOT_PASSWORD=root_password
Build and start the infrastructure:

bash
Copier le code
make
Docker Compose will:

Build all images

Create the network

Create and mount volumes

Start the containers in the correct order

Access
Website: https://mgobert.42.fr

WordPress Admin Panel: https://mgobert.42.fr/wp-admin

Design Choices & Technical Explanations
Virtual Machines vs Docker
Virtual Machines

Emulate full operating systems

Require more CPU, memory, and disk space

Slower to start and manage

Docker

Shares the host kernel

Lightweight and fast

Easier to deploy, version, and reproduce environments

Choice: Docker was selected for its efficiency, portability, and modularity, which perfectly fits the goals of the project.

Secrets vs Environment Variables
Docker Secrets

Encrypted and managed by Docker

Ideal for production environments and orchestration platforms

Environment Variables

Simple and readable

Stored locally in a .env file

Sufficient for a controlled academic environment

Choice: Environment variables were used as required by the subject.
The .env file is ignored by Git to avoid credential leaks.

Docker Network vs Host Network
Host Network

Containers share the host network stack

Less isolation

Increased attack surface

Docker Network

Isolated communication between containers

Fine-grained control over exposed services

Improved security

Choice: A custom Docker bridge network is used to isolate services and restrict access.

Docker Volumes vs Bind Mounts
Docker Volumes

Fully managed by Docker

Abstracted storage location

Bind Mounts

Direct mapping to a host directory

Explicit control over data location

Choice: Bind-mounted volumes mapped to /home/mgobert/data are used to ensure data persistence across container restarts, as required by the subject.

Resources
Documentation
Docker Documentation

Docker Compose Documentation

NGINX Documentation

WordPress Documentation

MariaDB Documentation

AI Usage
AI tools were used to:

Review Dockerfiles and configuration files

Verify compliance with the project subject

Improve documentation clarity and structure

All technical decisions and implementations were reviewed, fully understood, and validated by the author.

Author
mgobert
42 Student