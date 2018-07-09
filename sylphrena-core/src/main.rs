/*!
 * Sylphrena AI core program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

extern crate daemonize;

mod core;

use std::{thread, time, env, fs::File};
use daemonize::Daemonize;
use core::syl_core::Sylcore;

fn main() {
    println!("---=== Sylphrena-core started ===---");

	for argument in env::args() {
		if argument == "-help" || argument == "-h" {
			println!("List of available arguments:");
			println!("-h See the available arguments");
			println!("-d Start this application as daemon");
		}
		else if argument == "-d" {
    		let stdout = File::create("/tmp/sylphrena-core.out").unwrap();
    		let stderr = File::create("/tmp/sylphrena-core.err").unwrap();

    		let daemonize = Daemonize::new()
        		.pid_file("/tmp/sylphrena-core.pid") // Every method except `new` and `start`
        		.chown_pid_file(true)      // is optional, see `Daemonize` documentation
        		.working_directory("/tmp") // for default behaviour.
        		.user("root")
        		.group("daemon") // Group name
        		.group(2)        // or group id.
        		.umask(0o777)    // Set umask, `0o027` by default.
        		.stdout(stdout)  // Redirect stdout to `/tmp/sylphrena-core.out`.
        		.stderr(stderr)  // Redirect stderr to `/tmp/sylphrena-core.err`.
        		.privileged_action(|| "Executed before drop privileges");

    		match daemonize.start() {
        		Ok(_) => println!("Success, sylphrena-core daemonized"),
        		Err(e) => eprintln!("Error, {}", e),
    		}
		}
	}

	let mut core = Sylcore::new("syl-core");

	core.start_server();

	let mut counter = 0;
	loop {
		counter += 1;
		println!("One more step in the loop, count: {0}", counter);
		thread::sleep(time::Duration::from_millis(10000)); // set to 60000 when actually done with main method.
	}
}
