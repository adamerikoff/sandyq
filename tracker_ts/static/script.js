var _Tracker=(()=>{var n=class{url;siteID;referrer;ID;constructor(t,e,r){this.url=t,this.siteID=e,this.referrer=r;let i=this.getSession("ID");i&&(this.ID=i)}track(t,e){let r={tracking:{type:e=="Page Views"?"page":"event",event:t,identity:this.ID,ua:navigator.userAgent,category:e,referrer:this.referrer},site_id:this.siteID};this.trackRequest(r)}page(t){this.track(t,"Page views")}identify(t){this.ID=t,this.setSession("ID",t)}trackRequest(t){let e={method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify(t)};fetch(this.url,e).then(r=>{if(!r.ok)throw new Error("Network response was not ok");return r.json()}).then(r=>{console.log(r)}).catch(r=>{console.error("There was a problem with the fetch operation:",r)})}getSession(t){t=`__tracker_${t}__`;let e=sessionStorage.getItem(t);return e?JSON.parse(e):null}setSession(t,e){t=`__tracker_${t}__`,sessionStorage.setItem(t,JSON.stringify(e))}};((s,t)=>{let e=t.currentScript?.dataset;if(e){if(!e.siteid){console.error("you must have a data-siteid in your script tag!");return}}else{console.error("you must have a data-siteid in your script tag!");return}let r="",i=t.referrer;i&&i.indexOf(`${s.location.protocol}//${s.location.host}`)==0&&(r=i);let a=new n("http://0.0.0.0:9876/track",e.siteid,r),c=s.location.pathname;s._tracker=s._tracker||a,a.page(c),console.log("af"),s.addEventListener("hashchange",()=>{a.page(t.location.hash)},!1);let o=s.history;if(o.pushState){let g=o.pushState;o.pushState=function(){g.apply(this,arguments),a.page(s.location.pathname)},s.addEventListener("popstate",()=>{a.page(s.location.pathname)})}})(window,document);console.log("af");})();