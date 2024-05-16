import { Tracker } from "./Tracker.ts";

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
    console.log("af")
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
console.log("af");