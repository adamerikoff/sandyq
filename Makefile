.PHONY: start
start:
	@echo "Starting Golang API and ClickHouse..."
	docker-compose up -d
	@echo "Waiting for ClickHouse to start..."
	@sleep 10
	@$(MAKE) create-table

.PHONY: stop
stop:
	docker-compose down -v --rmi all --remove-orphans

create-table:
	@echo "Creating table in ClickHouse..."
	@CREATE_TABLE_QUERY="CREATE TABLE IF NOT EXISTS tracking_info ( \
		ip String, \
		page String, \
		agent String, \
		referrer String, \
		previous_page String \
	) ENGINE = MergeTree() \
	ORDER BY (page, referrer, previous_page);" && \
	docker-compose exec clickhouse bash -c "clickhouse-client --query=\"$${CREATE_TABLE_QUERY}\""
	@echo "Table created successfully."
