# Developer Documentation

---

## Setting Up the Environment from Scratch

### Prerequisites

- Linux-based OS
- Docker (version 20.0+)
- Docker Compose (version 1.29+)
- Make
- Git

### Project Structure

```
.
├── Makefile
├── docker-compose.yml
├── .env                    # Environment variables (Git ignored)
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
└── srcs/
    ├── nginx/
    │   ├── Dockerfile
    │   ├── nginx.conf
    │   └── ssl.sh
    ├── wordpress/
    │   ├── Dockerfile
    │   ├── www.conf
    │   └── entrypoint.sh
    └── mariadb/
        ├── Dockerfile
        ├── init.sql
        ├── 50-server.cnf
        └── entrypoint.sh
```

### Configuration

1. **Clone the repository:**
   ```bash
   git clone <repository_url>
   cd inception
   ```

2. **Create `.env` file:**
   ```bash
   cp .env.example .env
   ```
   
   Edit `.env` with your configuration:
   ```env
   DOMAIN_NAME=mgobert.42.fr
   MYSQL_DATABASE=wordpress
   MYSQL_USER=wp_user
   MYSQL_PASSWORD=strong_password
   MYSQL_ROOT_PASSWORD=root_password
   ```

3. **Create data directories:**
   ```bash
   mkdir -p /home/mgobert/data/mariadb
   mkdir -p /home/mgobert/data/wordpress
   ```

**Security:** Never commit `.env` to Git. Keep credentials private.

---

## Building and Launching with Makefile and Docker Compose

### Makefile Commands

```bash
make                # Build images and start all containers
make re             # Clean rebuild everything
make down           # Stop all containers
make fclean         # Remove all containers, images, and volumes
```

### What Happens During Build

1. Builds Docker images for NGINX, WordPress, and MariaDB
2. Creates a custom Docker bridge network
3. Creates named volumes for data persistence
4. Starts all containers in dependency order
5. Initializes the WordPress database (on first run)

---

## Managing Containers and Volumes

### Container Commands

```bash
docker compose ps                    # View container status
docker compose logs -f               # View real-time logs
docker compose logs -f nginx         # View NGINX logs only
docker compose restart               # Restart all services
docker exec -it inception_nginx bash # Enter NGINX container shell
```

### Volume Commands

```bash
docker volume ls                          # List all volumes
docker volume inspect inception_mariadb_volume   # View volume details
docker volume rm inception_mariadb_volume        # Delete a volume
```

---

## Data Storage and Persistence

### Where Data Is Stored

**MariaDB Data:**
- Container location: `/var/lib/mysql`
- Host location: `/home/mgobert/data/mariadb`
- Volume: `inception_mariadb_volume`
- Persists: Database files, users, WordPress content

**WordPress Files:**
- Container location: `/var/www/html`
- Host location: `/home/mgobert/data/wordpress`
- Volume: `inception_wordpress_volume`
- Persists: Website files, themes, plugins, media

### How Persistence Works

Data persists using **Docker volumes with bind mounts**:

1. Containers write data to volumes
2. Volumes are mounted to host directories
3. Data survives container restarts and removals
4. Host directories provide long-term storage

### Data Persistence Flow

- **Start containers** → Data is loaded from volumes
- **Stop containers** → Data remains in volumes
- **Restart containers** → Data is automatically restored
- **Delete volumes** → Data is permanently lost

### Backing Up Data

```bash
# Backup database
docker exec inception_mariadb mysqldump -uroot -p$MYSQL_ROOT_PASSWORD \
  --all-databases > backup.sql

# Backup WordPress files
tar czf wordpress_backup.tar.gz /home/mgobert/data/wordpress/
```

### Restoring Data

```bash
# Restore database
docker exec -i inception_mariadb mysql -uroot -p$MYSQL_ROOT_PASSWORD < backup.sql

# Restore WordPress files
tar xzf wordpress_backup.tar.gz -C /home/mgobert/data/
```

---

## Quick Reference

| Task | Command |
|------|---------|
| Build & start | `make` |
| Rebuild | `make re` |
| Stop | `make down` |
| Full cleanup | `make fclean` |
| Container status | `docker compose ps` |
| Logs | `docker compose logs -f` |
| List volumes | `docker volume ls` |
| Enter container | `docker exec -it <name> bash` |
