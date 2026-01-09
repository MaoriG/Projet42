*This project has been created as part of the 42 curriculum by mgobert.*

# Inception

## Description

**Inception** is a DevOps project from the 42 curriculum designed to understand and implement containerization concepts using Docker and Docker Compose.

### Project Goal

The objective is to design and deploy a secure, modular, and scalable web infrastructure using industry-standard containerization tools. The project demonstrates practical knowledge of service orchestration, networking, data persistence, and environment-based configuration.

### Overview

The infrastructure hosts a **WordPress website** served exclusively over **HTTPS**, backed by a **MariaDB database**, and exposed through an **NGINX reverse proxy and web server**. Each service runs in a dedicated container, communicating through a private Docker network while adhering to security best practices.

The project encompasses:
- Container orchestration with Docker Compose
- Service networking and isolation
- Volume management for data persistence
- HTTPS/TLS configuration
- Environment-based configuration
- Multi-container application architecture

---

## Instructions

### Prerequisites

Before running this project, ensure the following are installed:
- Linux-based operating system (or virtual machine)
- Docker (version 20+)
- Docker Compose (version 1.29+)
- Make

### Installation & Execution

1. **Clone the repository:**
   ```bash
   git clone <repository_url>
   cd inception
   ```

2. **Configure environment variables:**
   Create a `.env` file at the root of the project with the following variables:
   ```env
   DOMAIN_NAME=mgobert.42.fr
   MYSQL_DATABASE=wordpress
   MYSQL_USER=wp_user
   MYSQL_PASSWORD=strong_password
   MYSQL_ROOT_PASSWORD=root_password
   ```

3. **Build and start the infrastructure:**
   ```bash
   make
   ```
   This command will:
   - Build all custom Docker images
   - Create the isolated Docker network
   - Create and mount named volumes
   - Start all containers in the correct dependency order

4. **Verify the deployment:**
   - Website: https://mgobert.42.fr
   - WordPress Admin Panel: https://mgobert.42.fr/wp-admin

### Stopping & Cleaning

- Stop containers: `make stop`
- Remove containers: `make down`
- Full cleanup (volumes included): `make fclean`

---

## Project Description

### Architecture Overview

The infrastructure consists of three main services:

- **NGINX**
  - Reverse proxy and web server
  - Handles TLS/SSL encryption (HTTPS only)
  - The only container exposed to the host machine
  - Forwards requests to the PHP-FPM backend

- **WordPress (PHP-FPM)**
  - WordPress application server
  - Communicates with NGINX via FastCGI protocol
  - Connects to MariaDB for data persistence
  - Not directly exposed to the host

- **MariaDB**
  - Relational database management system
  - Stores WordPress data (posts, users, settings, etc.)
  - Completely isolated from the host (internal communication only)
  - Accessible only through the Docker network

All containers communicate via a **custom Docker bridge network**, ensuring isolation and security.

### Design Choices & Technical Explanations

#### Virtual Machines vs Docker

| Aspect | Virtual Machines | Docker Containers |
|--------|------------------|-------------------|
| **Overhead** | Emulates entire OS kernel | Shares host kernel |
| **Performance** | Slower startup (minutes) | Fast startup (seconds) |
| **Resource Usage** | High (CPU, memory, disk) | Lightweight and efficient |
| **Portability** | Heavy, environment-specific | Highly portable, "run anywhere" |
| **Isolation** | Strong but heavyweight | Good, with shared kernel |

**Choice:** Docker was selected for its efficiency, portability, and modularity. It perfectly aligns with the project's goals of demonstrating modern DevOps practices while maintaining lightweight deployments.

#### Secrets vs Environment Variables

| Aspect | Docker Secrets | Environment Variables |
|--------|----------------|----------------------|
| **Storage** | Encrypted, managed by Docker | Plain text in .env file |
| **Security** | High (production-grade) | Medium (academic environment) |
| **Deployment** | Swarm/Kubernetes mode | Local development, Docker Compose |
| **Complexity** | Higher | Simpler |

**Choice:** Environment variables are used as required by the project specification. The `.env` file is added to `.gitignore` to prevent accidental credential exposure to the repository.

#### Docker Network vs Host Network

| Aspect | Host Network | Docker Network (Bridge) |
|--------|--------------|------------------------|
| **Isolation** | No isolation; containers share host stack | Isolated communication channel |
| **Security** | Higher attack surface | Restricted, controlled access |
| **Container Access** | All access host network | Only containers on network can communicate |
| **Use Case** | Performance-critical applications | Most applications (recommended) |

**Choice:** A custom Docker bridge network isolates all services, restricting direct access to the host and limiting communication to intended services only. This enhances security and follows containerization best practices.

#### Docker Volumes vs Bind Mounts

| Aspect | Docker Volumes | Bind Mounts |
|--------|----------------|------------|
| **Management** | Fully managed by Docker | Manual management by user |
| **Storage Location** | Docker-managed (abstracted) | Specific host directory |
| **Data Portability** | Easy to backup and migrate | Tied to host directory structure |
| **Performance** | Optimized for containers | Slightly higher overhead on some systems |
| **Use Case** | Production, abstraction needed | Development, specific host access |

**Choice:** Bind-mounted volumes are used to map project data to `/home/mgobert/data` on the host, ensuring data persistence across container restarts and allowing easy access to data files as required by the project specification.

---

## Resources

### Documentation & References

- [Docker Official Documentation](https://docs.docker.com/)
- [Docker Compose Documentation](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress Documentation](https://wordpress.org/support/)
- [MariaDB Documentation](https://mariadb.com/kb/en/)
- [OWASP Security Best Practices](https://owasp.org/)

### AI Usage

AI tools were used for the following purposes:

- **Code Review & Optimization:** Reviewed Dockerfiles, docker-compose.yml, and NGINX configuration files to ensure best practices and compliance with the project requirements
- **Documentation:** Improved clarity and structure of technical documentation
- **Testing & Validation:** Verified configuration files against the project specification
- **Architecture Review:** Confirmed design choices align with industry standards

**Important Note:** All technical decisions, implementations, and configurations were thoroughly reviewed, fully understood, and validated by the author. The AI served as a supplementary tool for verification and documentation enhancement, not for core decision-making.

---

## Author

**mgobert**  
42 Student
