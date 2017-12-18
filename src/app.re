let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) => {
    /* our dummy data */
    <div className="App">
      <h1>{ReasonReact.stringToElement("Reason Projects")}</h1>
    </div>
  }
};
