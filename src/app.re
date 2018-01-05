type state = {repoData: option(RepoData.repo)};
type action =
  | Loaded(RepoData.repo);

let component = ReasonReact.reducerComponent("App");

/* our dummy data */
let dummyRepo: RepoData.repo = {
  stargazers_count: 27,
  full_name: "jsdf/reason-react-hacker-news",
  html_url: "https://github.com/jsdf/reason-react-hacker-news"
};

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
      | Some(repo) => <RepoItem repo=repo />
      | None => loadedReposButton
      };

    <div className="App">
      <h1>{ReasonReact.stringToElement("Reason Projects")}</h1>
      {repoItem}
    </div>
  }
};
