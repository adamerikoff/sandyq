## SandyqTracker

![architecture_design](https://github.com/adamerikoff/sandyq/blob/main/tracker.png?raw=true)

Web Analytics Tracker built with a combination of technologies:

* **Tracker.js** Implemented using JavaScript (TypeScript) for client-side tracking.
* **Backend:** Uses Golang for server-side functionality.
* **Database:** Leverages ClickHouse for efficient data storage and retrieval.
* **Dashboard (Future):** Plans include creating a dashboard to visualize tracking data.

### Project Goals

* Track user interactions and website usage data.
* Store the collected data in a scalable and performant database (ClickHouse).
* Provide a user-friendly interface (future dashboard) for analyzing and visualizing tracking data.

### Current Functionality (Backend)

* The Golang server listens for tracking data sent from the client (or potentially other sources).
* The server decodes and validates the received data.
* Stores the validated data in ClickHouse tables.

### Future Development

* .
* .

### Dependencies

* .
* .
* .

### Getting Started (Backend)

1. TOADD

### Usage (Backend)

The specific way to send tracking data to the server depends on your implementation. Here's a general concept:

* On the client-side (web application), you would likely use your client-side tracking library (to be developed) to capture user interactions and prepare the data for transmission.
* The library would then send the encoded data to the server endpoint (defined in the Golang code).

**Note:** This readme assumes a backend-focused project currently. Client-side integration and dashboard development will be added in the future.

### Contributing

We welcome contributions to this project! Please create pull requests for any improvements or new features.

### License

MIT
