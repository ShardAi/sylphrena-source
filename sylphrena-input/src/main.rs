/*!
 * Sylphrena AI input program - https://github.com/ShardAi
 * Version - 1.0.0.0
 *
 * Copyright (c) 2017 Eirik Skjeggestad Dale
 */

extern crate daemonize;

mod input;

use std::{thread, time, env};
use std::fs::File;
use daemonize::Daemonize;
use input::syl_input::Sylinput;

fn main() {
    println!("---=== Sylphrena-input started ===---");

	for argument in env::args() {
		if argument == "-help" || argument == "-h" {
			println!("List of available arguments:");
			println!("-h See the available arguments");
			println!("-d Start this application as daemon");
		}
		else if argument == "-d" {
    		let stdout = File::create("/tmp/sylphrena-input.out").unwrap();
    		let stderr = File::create("/tmp/sylphrena-input.err").unwrap();

    		let daemonize = Daemonize::new()
        		.pid_file("/tmp/sylphrena-input.pid") // Every method except `new` and `start`
        		.chown_pid_file(true)      // is optional, see `Daemonize` documentation
        		.working_directory("/tmp") // for default behaviour.
        		.user("root")
        		.group("daemon") // Group name
        		.group(2)        // or group id.
        		.umask(0o777)    // Set umask, `0o027` by default.
        		.stdout(stdout)  // Redirect stdout to `/tmp/sylphrena-input.out`.
        		.stderr(stderr)  // Redirect stderr to `/tmp/sylphrena-input.err`.
        		.privileged_action(|| "Executed before drop privileges");

    		match daemonize.start() {
        		Ok(_) => println!("Success, sylphrena-input daemonized"),
        		Err(e) => eprintln!("Error, {}", e),
    		}
		}
	}

	let mut syl_input = Sylinput::new("syl-input");

	syl_input.train_nlp();
	syl_input.start_client();

	println!("Entering sleep mode. Restart application to initiate new contact with server.");
	let mut counter = 0;
	loop {
		counter += 1;
		println!("One more step in the loop, count: {0}", counter);
		thread::sleep(time::Duration::from_millis(10000)); // set to 60000 when actually done with main method.
	}
}
