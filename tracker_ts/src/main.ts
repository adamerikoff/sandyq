import { Tracker, TrackPayload } from "./tracker";

((window, document) => {
    const ds = document.currentScript?.dataset;
    if (!ds) {
        console.error("no data_siteID in script tag!");
        return;
    } else if (!ds.siteID) {
        console.error("no data_siteID in script tag!");
        return;
    }
    
    if (!window._tracker) {
        const referrer: string = document.referrer;
        const agent: string = window.navigator.userAgent;
        const URL: string = "localhost:8080";
        let tracker: Tracker = new Tracker(ds.siteID, referrer, agent, URL)

        
    } else {
        window._tracker = window._tracker;

        const page: string = window.location.pathname;
        const previousPage: string = document.referrer;


        const payload: TrackPayload = window._tracker.buildTrackPayload(page, previousPage);
        window._tracker.sendTrackingData(payload);
    }

    function track(w, d) : void {
        const page: string = w.location.pathname;
        const previousPage: string = d.referrer;


        const payload: TrackPayload = w._tracker.buildTrackPayload(page, previousPage);
        w._tracker.sendTrackingData(payload);
    }
    
})(window, document);