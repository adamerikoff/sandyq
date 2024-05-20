package main

import (
	"context"
	"fmt"
	"log"

	"github.com/ClickHouse/clickhouse-go/v2"
)

func insertIntoClickHouse(conn clickhouse.Conn, data ClickHouseTrackingModel) {
	ctx := context.Background()

	batch, err := conn.PrepareBatch(ctx, "INSERT INTO tracking_table (ip, siteID, page, agent, referrer, previousPage)")

	if err != nil {
		log.Fatalf("Failed to prepare batch: %v", err)
	}

	err = batch.Append(data.IP, data.SiteID, data.Page, data.Agent, data.Referrer, data.PreviousPage)

	if err != nil {
		log.Fatalf("Failed to append data: %v", err)
	}

	if err := batch.Send(); err != nil {
		log.Fatalf("Failed to send batch: %v", err)
	}

	fmt.Println("Data inserted successfully!")
}
