#ifndef SOCKETUTILS_H
#define SOCKETUTILS_H

#include <QByteArray>
#include <QString>

#include <QtOpcUa/QOpcUaProvider>
#include <QtOpcUa/QOpcUaKeyPair>
#include <QtOpcUa/QOpcUaX509CertificateSigningRequest>
#include <QtOpcUa/QOpcUaX509ExtensionSubjectAlternativeName>
#include <QtOpcUa/QOpcUaX509ExtensionBasicConstraints>
#include <QtOpcUa/QOpcUaX509ExtensionKeyUsage>
#include <QFile>

static QByteArray GetFourByteArray(const int& num) {
    QByteArray result;

    char clist[4];
    clist[3] = uint8_t(num);
    clist[2] = uint8_t(num >> 8);
    clist[1] = uint8_t(num >> 16);
    clist[0] = uint8_t(num >> 24);

    result += clist[0];
    result += clist[1];
    result += clist[2];
    result += clist[3];
    return result;
}

static void CreatePrivateKeyAndCertificate(const QString& private_key_path, const QString& certificate_path) {
    // Generate RSA Key
    QOpcUaKeyPair key;
    key.generateRsaKey(QOpcUaKeyPair::RsaKeyStrength::Bits2048);

    // Save private key to file
    QByteArray keyData = key.privateKeyToByteArray(QOpcUaKeyPair::Cipher::Aes128Cbc, "");

    QFile keyFile(private_key_path);
    keyFile.open(QFile::WriteOnly);
    keyFile.write(keyData);
    keyFile.close();

    // Create a certificate signing request
    QOpcUaX509CertificateSigningRequest csr;

    // Set the subject of the certificate
    QOpcUaX509DistinguishedName dn;
    dn.setEntry(QOpcUaX509DistinguishedName::Type::CommonName, "hmi");
    dn.setEntry(QOpcUaX509DistinguishedName::Type::CountryName, "DE");
    dn.setEntry(QOpcUaX509DistinguishedName::Type::LocalityName, "Berlin");
    dn.setEntry(QOpcUaX509DistinguishedName::Type::StateOrProvinceName, "Berlin");
    dn.setEntry(QOpcUaX509DistinguishedName::Type::OrganizationName, "The Qt Company");
    csr.setSubject(dn);

    // The subject alternative name extension is needed for OPC UA
//    QOpcUaX509ExtensionSubjectAlternativeName *san = new QOpcUaX509ExtensionSubjectAlternativeName;
//    san->addEntry(QOpcUaX509ExtensionSubjectAlternativeName::Type::DNS, "foo.com");
//    san->addEntry(QOpcUaX509ExtensionSubjectAlternativeName::Type::URI, "urn:foo.com:The%20Qt%20Company:QtOpcUaViewer");
//    san->setCritical(true);
//    csr.addExtension(san);

    // Set the certificate basic constraints
    auto *bc = new QOpcUaX509ExtensionBasicConstraints;
    bc->setCa(false);
    bc->setCritical(true);
    csr.addExtension(bc);

    // Set the key usage constraints
    auto *ku = new QOpcUaX509ExtensionKeyUsage;
    ku->setCritical(true);
    ku->setKeyUsage(QOpcUaX509ExtensionKeyUsage::KeyUsage::DigitalSignature);
    ku->setKeyUsage(QOpcUaX509ExtensionKeyUsage::KeyUsage::NonRepudiation);
    ku->setKeyUsage(QOpcUaX509ExtensionKeyUsage::KeyUsage::KeyEncipherment);
    ku->setKeyUsage(QOpcUaX509ExtensionKeyUsage::KeyUsage::DataEncipherment);
    ku->setKeyUsage(QOpcUaX509ExtensionKeyUsage::KeyUsage::CertificateSigning);
    csr.addExtension(ku);

    // Now there are two options:
    // 1. When you need to get your certificate signing request signed by a certificate authority
    //    you have to use the request data.
    // 2. When there is no certificate authority you have to self-sign the request.

    // Option 1
//    QByteArray certificateSigingRequestData = csr.createRequest(key);

    // Option 2
    QByteArray selfSignedCertificateData = csr.createSelfSignedCertificate(key);

    QFile certFile(certificate_path);
    certFile.open(QFile::WriteOnly);
    certFile.write(selfSignedCertificateData);
    certFile.close();
}

#endif // SOCKETUTILS_H
