#include "binary-cache-store.hh"

namespace nix {

struct HttpBinaryCacheStoreConfig : virtual BinaryCacheStoreConfig
{
    using BinaryCacheStoreConfig::BinaryCacheStoreConfig;

    HttpBinaryCacheStoreConfig(std::string_view scheme, std::string_view _cacheUri, const Params & params);

    Path cacheUri;

    const Setting<std::string> sslCert{this, "", "ssl-cert", "An optional SSL client certificate in PEM format; see CURLOPT_SSLCERT."};

    const Setting<std::string> sslKey{this, "", "ssl-key", "The SSL client certificate key in PEM format; see CURLOPT_SSLKEY."};

    const std::string name() override
    {
        return "HTTP Binary Cache Store";
    }

    static std::set<std::string> uriSchemes()
    {
        static bool forceHttp = getEnv("_NIX_FORCE_HTTP") == "1";
        auto ret = std::set<std::string>({"http", "https"});
        if (forceHttp)
            ret.insert("file");
        return ret;
    }

    std::string doc() override;
};

}
