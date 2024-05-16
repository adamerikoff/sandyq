export interface TrackingData {
    type: "event" | "page";
    identity: string;
    ua: string;
    event: string;
    category: string;
    referrer: string;
}

export interface TrackPayload {
    tracking: TrackingData;
    site_id: string;
}

export class Tracker {
    private url: string;
    private siteID: string;
    private referrer: string;
    private ID: string;

    constructor(url: string, siteID: string, referrer: string) {
        this.url = url;
        this.siteID = siteID;
        this.referrer = referrer;

        const customID = this.getSession("ID");
        if (customID) {
            this.ID = customID;
        }
    }

    public track(event: string, category: string) {
        const payload: TrackPayload = {
            tracking: {
                type: category == "Page Views" ? "page" : "event",
                event: event,
                identity: this.ID,
                ua: navigator.userAgent,
                category: category,
                referrer: this.referrer,
            },
            site_id: this.siteID,
        };
        this.trackRequest(payload)
    }

    public page(path: string) {
        this.track(path, "Page views");
    }

    public identify(customID: string) {
        this.ID = customID;
        this.setSession("ID", customID);
    }

    private trackRequest(payload: TrackPayload) {
        const options: RequestInit = {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(payload)
        };
        fetch(this.url, options)
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            console.log(data);
        })
        .catch(error => {
            console.error('There was a problem with the fetch operation:', error);
        });
    }

    private getSession(key) {
        key = `__tracker_${key}__`;
        const s = sessionStorage.getItem(key);
        if (!s) return null;
        return JSON.parse(s);
    }

    private setSession(key: string, value: any) {
        key = `__tracker_${key}__`;
        sessionStorage.setItem(key, JSON.stringify(value));
    }
}