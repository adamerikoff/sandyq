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
	@CREATE_TABLE_QUERY="CREATE TABLE IF NOT EXISTS tracking_table ( \
		ip String, \
		siteID String, \
		page String, \
		agent String, \
		referrer String, \
		previousPage String \
	) ENGINE = MergeTree() \
	ORDER BY (siteID, page, referrer, previousPage);" && \
	docker-compose exec clickhouse bash -c "clickhouse-client --query=\"$${CREATE_TABLE_QUERY}\""
	@echo "Table created successfully."