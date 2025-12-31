NAME = inception

COMPOSE = docker compose
COMPOSE_FILE = docker-compose.yml

all: up

up:
	$(COMPOSE) -f $(COMPOSE_FILE) up -d --build

down:
	$(COMPOSE) -f $(COMPOSE_FILE) down

re:
	$(COMPOSE) -f $(COMPOSE_FILE) down --volumes
	$(COMPOSE) -f $(COMPOSE_FILE) up -d --build

clean:
	$(COMPOSE) -f $(COMPOSE_FILE) down

fclean:
	$(COMPOSE) -f $(COMPOSE_FILE) down --volumes --rmi all

logs:
	$(COMPOSE) -f $(COMPOSE_FILE) logs -f

ps:
	$(COMPOSE) -f $(COMPOSE_FILE) ps

.PHONY: all up down re clean fclean logs ps
