Pod::Spec.new do |s|
    s.name         = "Rhea"
    s.version      = '0.2.4'
    s.summary      = "A modern c++ constraint solver based on Cassowary."
    s.homepage     = "https://github.com/Nocte-/rhea"
    s.authors      = {
    	"Nocte" => "nocte@hippie.nu"
    	}
    s.license      = 'MIT'
    s.source       = {
        :git => "https://github.com/Nocte-/rhea.git",
        :tag => s.version.to_s
        }
    s.ios.deployment_target = '6.0'
    s.osx.deployment_target = '10.8'
    s.library = 'c++'
    s.pod_target_xcconfig = {
       'CLANG_CXX_LANGUAGE_STANDARD' => 'c++11',
       'CLANG_CXX_LIBRARY' => 'libc++'
    }
    s.source_files  = 'rhea/**/*.{h,hpp,cpp,c,m}'
    s.exclude_files = 'rhea/parser.hpp'
end
