interface TrackingData {
    type: "event" | "page";
    identity: string;
    ua: string;
    event: string;
    category: string;
    referrer: string;
}

interface TrackPayload {
    tracking: TrackingData;
    site_id: string;
}

class Tracker {
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
        const encodedPayload = btoa(JSON.stringify(payload));
        const url_string = `${this.url}?data=${encodedPayload}`;
        console.log(encodedPayload)
        console.log(atob(encodedPayload))
        const img = new Image(1, 1); // Create a 1x1 pixel image
        img.onerror = img.onload = () => { /* No need to handle response */ };
        img.src = url_string;
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



((window, document) => {
    const ds = document.currentScript?.dataset;
    if (!ds) {
        console.error("you must have a data-siteid in your script tag!");
        return;
    } else if (!ds.siteid) {
        console.error("you must have a data-siteid in your script tag!");
        return;
    }
    let externalReferrer = "";
    const ref = document.referrer;
    if (ref && ref.indexOf(`${window.location.protocol}//${window.location.host}`) == 0) {
        externalReferrer = ref;
    }
    let tracker = new Tracker("http://0.0.0.0:9876/track", ds.siteid, externalReferrer);
    const path = window.location.pathname;
    window._tracker = window._tracker || tracker;
    tracker.page(path)
    window.addEventListener(
        "hashchange",
        () => {
            tracker.page(document.location.hash);
        },
        false
    );
    const history = window.history;
    if (history.pushState) {
        const originalFn = history["pushState"];
        history.pushState = function () {
            originalFn.apply(this, arguments);
            tracker.page(window.location.pathname);
        };

        window.addEventListener(
            "popstate",
            () => {
                tracker.page(window.location.pathname);
            }
        )
    }
})(window, document);

