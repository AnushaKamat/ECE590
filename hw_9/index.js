//AWS Lambda Server Function
//Takes in 2 doubles "x", "y" and a string"op" in the body.
// Body template:
// "body" ="{/"x/":1.2,/"y/":1.3,/"op/":/"add/"}"
//returns :
// {"result" : 2.5}
// in case of error:
//returns :
// {"error" :"missing keys"} //or unknown operator, improper JSON

exports.handler = async (event) => {
    
    let ans = 0.0;
    let msg = "";
    let body = "";
    if ( event.hasOwnProperty("x") && event.hasOwnProperty("y") && event.hasOwnProperty("op")) {
        try {
            if (event["op"]=="multiply") {
                ans = event["x"] * event["y"];
            } else if (event["op"]=="divide") {
                ans = event["x"] / event["y"];
            } else if (event["op"]=="add") {
                ans = event["x"] + event["y"];
            } else if (event["op"]=="subtract") {
                ans = event["x"] - event["y"];
            } else {
                msg = "unknown operator: " + event["op"];
            }
        } catch (e) {
            msg = "error: " + e;
        }
    } else {
        msg = "Missing keys";
    }
    
    if (msg == "") {
        body = ans.toString();
    } else {
        body = msg;
    }
    const response = {
        statusCode: 200,
        body: body,
    };
    return response;
};