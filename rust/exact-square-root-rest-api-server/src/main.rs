mod exact_root;

use axum::{
    extract::Path,
    routing::get,
    Json, Router,
};
use serde::Serialize;
use tokio::net::TcpListener;

#[derive(Serialize)]
struct Result {
    multiplicator: i64,
    sqrt: i64,
}

#[tokio::main]
async fn main() {
    let app = Router::new()
        .route("/exactSquareRoot/:param", get(exact_square_root));

    let listener = TcpListener::bind("127.0.0.1:8083")
        .await
        .unwrap();

    println!("Server läuft auf http://localhost:8083");

    axum::serve(listener, app).await.unwrap();
}

async fn exact_square_root(Path(param): Path<i64>) -> Json<Vec<Result>> {
  use crate::exact_root::exact_root::get_exact_sqrt;

  let results = get_exact_sqrt(param);
  let mut json_results: Vec<Result> = vec![];
  for r in results {
    json_results.push(Result{multiplicator: r.multiplicator, sqrt: r.sqrt})
  }
  Json(json_results)
}