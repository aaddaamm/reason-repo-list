type state = {repoData: option(array(RepoData.repo))};

type action =
  | Loaded(array(RepoData.repo));

let component = ReasonReact.reducerComponent("App");

/* our dummy data */
let dummyRepo: array(RepoData.repo) = [|
  RepoData.parseRepoJson(
    Js.Json.parseExn(
      {js|
        {
          "stargazers_count": 93,
          "full_name": "reasonml/reason-tools",
          "html_url": "https://github.com/reasonml/reason-tools"
        }
      |js}
    )
  )
|];

let make = (_children) => {
  ...component,
  reducer: (action, _state) => {
    switch action {
    | Loaded(loadedRepo) =>
      ReasonReact.Update({
        repoData: Some(loadedRepo)
      })
    }
  },
  initialState: () => {
    repoData: None
  },
  render: (self) => {
    let loadedReposButton =
      <button onClick=self.reduce((_event) => Loaded(dummyRepo))>
        {ReasonReact.stringToElement("Load Repos")}
      </button>;

    let repoItem =
      switch (self.state.repoData) {
      | Some(repos) => ReasonReact.arrayToElement(
          Array.map(
            (repo: RepoData.repo) => <RepoItem key=repo.full_name repo=repo />,
            repos
          )
        )
      | None => loadedReposButton
      };

    <div className="App">
      <h1>{ReasonReact.stringToElement("Reason Projects")}</h1>
      {repoItem}
    </div>
  }
};
