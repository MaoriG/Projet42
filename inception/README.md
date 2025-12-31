# Inception

*This project has been created as part of the 42 curriculum by mgobert.*

## Description

Inception is a DevOps project from the 42 curriculum that deploys a secure WordPress infrastructure using Docker and Docker Compose.

The stack consists of:
- **NGINX** – Web server with HTTPS only
- **WordPress with PHP-FPM** – Content management system
- **MariaDB** – Relational database

Each service runs in its own container and communicates through a private Docker network for enhanced security and modularity.

---

## Prerequisites

- Linux virtual machine
- Docker
- Docker Compose
- Make

---

## Quick Start

1. Create a `.env` file at the root of the project with your configuration
2. Run:
   ```bash
   make
   ```

---

## Design Choices

### Docker over Virtual Machines
Virtual Machines emulate full operating systems and are resource-intensive. Docker containers share the host kernel, making them lightweight, faster to deploy, and easier to manage. Docker was chosen for its efficiency, portability, and modular architecture.

### Environment Variables vs Secrets
Environment variables stored in a local `.env` file configure services. The `.env` file is ignored by Git to prevent credential leaks. Docker secrets provide stronger security but are unnecessary for this project scope.

### Custom Docker Network
A custom Docker bridge network isolates containers and allows controlled communication. This approach is more secure than exposing services directly to the host network.

### Docker Volumes with Bind Mounts
Docker volumes abstract storage management, but bind-mounted volumes mapped to `/home/mgobert/data` ensure data persistence across container restarts as required by the subject.

---

## Access

- **Website:** https://mgobert.42.fr
- **WordPress Admin Panel:** https://mgobert.42.fr/wp-admin

---

## Resources

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Documentation](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress Documentation](https://wordpress.org/documentation/)
- [MariaDB Documentation](https://mariadb.com/kb/en/)

---

## AI Usage

AI tools were used to:
- Review Dockerfiles and configuration files
- Verify compliance with the project subject
- Improve documentation clarity and structure

All technical choices and implementations were reviewed, understood, and validated by the author.