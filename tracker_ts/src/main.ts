import { Tracker, TrackPayload } from "./tracker";

((window, document) => {
    console.log("Started script!")
    const ds = document.currentScript?.dataset;
    if (!ds) {
        console.error("no data_siteid in script tag!");
        return;
    } else if (!ds.siteid) {
        console.error("no data_siteid in script tag!");
        return;
    }
    
    if (!window._tracker) {
        console.log("Creating Tracker object!")

        const referrer: string = document.referrer;
        const agent: string = window.navigator.userAgent;
        const URL: string = "http://localhost:8080/track";
        const siteID = ds.siteid

        window._tracker = new Tracker(siteID, referrer, agent, URL)
        track(window, document);
    } else {
        console.log("Tracker already exists!")
    }

    function track(w, d) : void {
        const page: string = w.location.pathname;
        const previousPage: string = d.referrer;


        const payload: TrackPayload = w._tracker.buildTrackPayload(page, previousPage);
        w._tracker.sendTrackingData(payload);
        console.log("Payload send: ", payload);
    }
    
})(window, document);