'use strict';

module.exports = function(grunt) {
	// Unified Watch Object
	var watchFiles = {
		tesi: ['tesi.tex'],
		capitoli: ['capitoli/*.tex'],
		inizioFine: ['inizio-fine/*.tex']
	};


	// Project Configuration
	grunt.initConfig({
		pkg: grunt.file.readJSON('package.json'),
		notify_hooks: {
			options: {
				enabled: true,
				title: "Premi - Test",
				success: true, // whether successful grunt executions should be notified automatically
				duration: 3 // the duration of notification in seconds, for `notify-send only
			}
		},
		watch: {
			capitoli: {
				files: watchFiles.capitoli,
				tasks: ['shell:build', 'shell:clean'],
				options: {
					livereload: true
				}
			},
			tesi: {
				files: watchFiles.tesi,
				tasks: ['shell:build', 'shell:clean'],
				options: {
					livereload: true
				}
			},
			inizioFine: {
				files: watchFiles.inizioFine,
				tasks: ['shell:build', 'shell:clean'],
				options: {
					livereload: true
				}
			}
		},
		shell: {
	        build: {
	            command: 'bash tesi-build.sh'
        	},
        	clean: {
	            command: 'bash tesi-clean.sh'
        	}
    	},
    	concurrent: {
			default: ['watch'],
			options: {
				logConcurrentOutput: true,
				limit: 10
			}
		}
	});

	require('load-grunt-tasks')(grunt);
	grunt.loadNpmTasks('grunt-notify');
	grunt.loadNpmTasks('grunt-contrib-watch');

	// Making grunt default to force in order not to break the project.
	grunt.option('force', true);


	// Default task(s).
	grunt.registerTask('default', ['shell:build','shell:clean','concurrent:default']);


	grunt.registerTask('clean', ['shell:clean']);
	grunt.registerTask('build', ['shell:build']);
};
