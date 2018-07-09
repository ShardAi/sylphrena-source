/*!
 * Sylphrena AI core program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

use core::syl_tcp::Syltcp;

const LOCAL: &str = "127.0.0.1:8888";

pub struct Sylcore {
    id: String,
    tcp_server: Syltcp,
}

impl Sylcore {
    pub fn new(id: &str) -> Sylcore {
        let core = Sylcore{
            id: id.to_string(),
            tcp_server: Syltcp::new("syl-tcp", LOCAL)
        };
        println!("Created {0}!", core.id.to_string());
        return core;
    }
    pub fn start_server(&mut self) {
        self.tcp_server.start_server();
    }
}