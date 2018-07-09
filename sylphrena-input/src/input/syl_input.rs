/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

use input::syl_client::Sylclient;

pub struct Sylinput{
    id: String,
    client: Sylclient
}

impl Sylinput {
    pub fn new(id: &str) -> Sylinput{
        let input = Sylinput {
            id: id.to_string(),
            client: Sylclient::new("syl-client", "127.0.0.1:8888")
        };
        println!("Created {}!", input.id.to_string());
        return input;
    }

    pub fn start_client(&mut self) {
        println!("Starting client for {}.", self.id.to_string());
        self.client.start();
    }
}