#include "groundwaterdialog.h"
#include "groundwaterdialogmodel.h"
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QButtonGroup>
#include <QLayout>
#include <QDebug>
#include <QStyle>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

GroundwaterDialog::GroundwaterDialog(bool isMSE, const GroundwaterDialogModel& initialData, QWidget* parent)
: QDialog(parent), m_isMSE(isMSE), m_currentData(initialData)
{
    setupUi(isMSE);
    loadUiData(initialData);

    // To make sure the controls are properly enabled/disabled regardless of
    // the above data load ordering.
    enableWaterTableGroupWidgets(m_includeWaterTableCheckbox->isChecked());

    setTabOrder(m_includeWaterTableCheckbox, m_waterTableGroupBox);
    setTabOrder(m_waterTableGroupBox, m_constantRadioButton);
    setTabOrder(m_constantRadioButton, m_waterElevationLineEdit);
    setTabOrder(m_waterElevationLineEdit, m_differentialRadioButton);
    setTabOrder(m_differentialRadioButton, m_backslopeWaterElevationLineEdit);
    setTabOrder(m_backslopeWaterElevationLineEdit, m_frontFaceWaterElevationLineEdit);

    if (m_isMSE) {
        setTabOrder(m_frontFaceWaterElevationLineEdit, m_infiltratesReinforcedZoneCheckbox);
        setTabOrder(m_infiltratesReinforcedZoneCheckbox, m_applyToAllSectionsCheckbox);

    } else {
        setTabOrder(m_frontFaceWaterElevationLineEdit, m_applyToAllSectionsCheckbox);
    }

    setTabOrder(m_applyToAllSectionsCheckbox, m_okCancelButtonBox->button(QDialogButtonBox::Ok));
    setTabOrder(m_okCancelButtonBox->button(QDialogButtonBox::Ok), m_okCancelButtonBox->button(QDialogButtonBox::Cancel));
    // m_okCancelButtonBox->button(QDialogButtonBox::Cancel)->setFocus();
}

GroundwaterDialog::~GroundwaterDialog()
{
}

void GroundwaterDialog::applyToAllSectionsHolderFunction(bool checked)
{
    qDebug() << "Placeholder: Apply to all sections = " << checked;
}

void GroundwaterDialog::enableWaterTableGroupWidgets(bool checked)
{
    m_waterTableGroupBox->setEnabled(checked);

    if (checked) {
        m_waterElevationLabel->setEnabled(m_constantRadioButton->isChecked());
        m_waterElevationLineEdit->setEnabled(m_constantRadioButton->isChecked());

        m_backslopeWaterElevationLabel->setEnabled(m_differentialRadioButton->isChecked());
        m_backslopeWaterElevationLineEdit->setEnabled(m_differentialRadioButton->isChecked());
        m_frontFaceWaterElevationLabel->setEnabled(m_differentialRadioButton->isChecked());
        m_frontFaceWaterElevationLineEdit->setEnabled(m_differentialRadioButton->isChecked());
    }
}

void GroundwaterDialog::updateElevationBuddyLabel(const QString& text)
{
    QString unit;

    if (text.contains("m")) {
        unit = "m";
    } else if (text.contains("ft")) {
        unit = "ft";
    } else {
        return;
    }

    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());

    if (lineEdit == NULL) {
        return;
    }

    if (lineEdit == m_waterElevationLabel->buddy()) {
        m_waterElevationLabel->setText(QString("Water elevation (%1):").arg(unit));
    } else if (lineEdit == m_backslopeWaterElevationLabel->buddy()) {
        m_backslopeWaterElevationLabel->setText(QString("Backslope water elevation (%1):").arg(unit));
    } else if (lineEdit == m_frontFaceWaterElevationLabel->buddy()) {
        m_frontFaceWaterElevationLabel->setText(QString("Front face water elevation (%1):").arg(unit));
    }
}

void GroundwaterDialog::accept()
{
    saveUiData();
    QDialog::accept();
}

void GroundwaterDialog::setupUi(bool isMSE)
{
    setWindowTitle("Define Groundwater");

    m_includeWaterTableCheckbox = new QCheckBox("Include water table");

    m_waterTableGroupBox = new QGroupBox("Water Profile");
    m_waterTableGroupBox->setCheckable(false);
    connect(m_includeWaterTableCheckbox, &QCheckBox::clicked, this, &GroundwaterDialog::enableWaterTableGroupWidgets);

    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression(R"([-+]?[0-9]*\.?[0-9]+(?:\s*(?:ft|m))?)"), this);

    m_constantRadioButton = new QRadioButton("Constant");
    int radioTextLeftMargin = m_constantRadioButton->style()->pixelMetric(QStyle::PM_RadioButtonLabelSpacing, nullptr, m_constantRadioButton);
    radioTextLeftMargin += m_constantRadioButton->style()->pixelMetric(QStyle::PM_ExclusiveIndicatorWidth, nullptr, m_constantRadioButton);

    m_waterElevationLabel = new QLabel("Water elevation (ft):");
    m_waterElevationLabel->setContentsMargins(radioTextLeftMargin, 0, 0, 0);
    m_waterElevationLineEdit = new QLineEdit("0");
    m_waterElevationLineEdit->setFixedWidth(75);
    m_waterElevationLineEdit->setValidator(validator);
    m_waterElevationLabel->setBuddy(m_waterElevationLineEdit);
    connect(m_waterElevationLineEdit, &QLineEdit::textEdited, this, &GroundwaterDialog::updateElevationBuddyLabel);
    connect(m_constantRadioButton, &QRadioButton::toggled, m_waterElevationLabel, &QLabel::setEnabled);
    connect(m_constantRadioButton, &QRadioButton::toggled, m_waterElevationLineEdit, &QLineEdit::setEnabled);

    m_differentialRadioButton = new QRadioButton("Differential");
    radioTextLeftMargin = m_differentialRadioButton->style()->pixelMetric(QStyle::PM_RadioButtonLabelSpacing, nullptr, m_differentialRadioButton);
    radioTextLeftMargin += m_differentialRadioButton->style()->pixelMetric(QStyle::PM_ExclusiveIndicatorWidth, nullptr, m_differentialRadioButton);

    m_backslopeWaterElevationLabel = new QLabel("Backslope water elevation (ft):");
    m_backslopeWaterElevationLabel->setContentsMargins(radioTextLeftMargin, 0, 0, 0);
    m_backslopeWaterElevationLineEdit = new QLineEdit("0");
    m_backslopeWaterElevationLineEdit->setFixedWidth(75);
    m_backslopeWaterElevationLineEdit->setValidator(validator);
    m_backslopeWaterElevationLabel->setBuddy(m_backslopeWaterElevationLineEdit);
    connect(m_backslopeWaterElevationLineEdit, &QLineEdit::textEdited, this, &GroundwaterDialog::updateElevationBuddyLabel);
    connect(m_differentialRadioButton, &QRadioButton::toggled, m_backslopeWaterElevationLabel, &QLabel::setEnabled);
    connect(m_differentialRadioButton, &QRadioButton::toggled, m_backslopeWaterElevationLineEdit, &QLineEdit::setEnabled);

    m_frontFaceWaterElevationLabel = new QLabel("Front face water elevation (ft):");
    m_frontFaceWaterElevationLabel->setContentsMargins(radioTextLeftMargin, 0, 0, 0);
    m_frontFaceWaterElevationLineEdit = new QLineEdit("0");
    m_frontFaceWaterElevationLineEdit->setFixedWidth(75);
    m_frontFaceWaterElevationLineEdit->setValidator(validator);
    m_frontFaceWaterElevationLabel->setBuddy(m_frontFaceWaterElevationLineEdit);
    connect(m_frontFaceWaterElevationLineEdit, &QLineEdit::textEdited, this, &GroundwaterDialog::updateElevationBuddyLabel);
    connect(m_differentialRadioButton, &QRadioButton::toggled, m_frontFaceWaterElevationLabel, &QLabel::setEnabled);
    connect(m_differentialRadioButton, &QRadioButton::toggled, m_frontFaceWaterElevationLineEdit, &QLineEdit::setEnabled);

    if (isMSE) {
        m_infiltratesReinforcedZoneCheckbox = new QCheckBox("Infiltrates reinforced zone");
    }

    m_applyToAllSectionsCheckbox = new QCheckBox("Apply to all sections");
    connect(m_applyToAllSectionsCheckbox, &QCheckBox::clicked, this, &GroundwaterDialog::applyToAllSectionsHolderFunction);

    m_okCancelButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    m_okCancelButtonBox->setOrientation(Qt::Orientation::Horizontal);
    connect(m_okCancelButtonBox, &QDialogButtonBox::accepted, this, &GroundwaterDialog::accept);
    connect(m_okCancelButtonBox, &QDialogButtonBox::rejected, this, &GroundwaterDialog::reject);

    QButtonGroup* radioButtonGroup = new QButtonGroup(this);
    {
        radioButtonGroup->addButton(m_constantRadioButton);
        radioButtonGroup->addButton(m_differentialRadioButton);
        radioButtonGroup->setExclusive(true);
    }

    QGridLayout* groupBoxLayout = new QGridLayout(m_waterTableGroupBox);
    groupBoxLayout->addWidget(m_constantRadioButton, 0, 0, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->addWidget(m_waterElevationLabel, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->addWidget(m_waterElevationLineEdit, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->addWidget(m_differentialRadioButton, 2, 0, 1, 2, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->addWidget(m_backslopeWaterElevationLabel, 3, 0, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->addWidget(m_backslopeWaterElevationLineEdit, 3, 1, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->addWidget(m_frontFaceWaterElevationLabel, 4, 0, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->addWidget(m_frontFaceWaterElevationLineEdit, 4, 1, Qt::AlignLeft | Qt::AlignVCenter);
    groupBoxLayout->setHorizontalSpacing(50);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_includeWaterTableCheckbox, 0, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(m_waterTableGroupBox, 0, Qt::AlignLeft | Qt::AlignVCenter);
    if (isMSE) {
        mainLayout->addWidget(m_infiltratesReinforcedZoneCheckbox, 0, Qt::AlignLeft | Qt::AlignVCenter);
    }
    mainLayout->addWidget(m_applyToAllSectionsCheckbox, 0, Qt::AlignLeft | Qt::AlignVCenter);
    mainLayout->addWidget(m_okCancelButtonBox, 0, Qt::AlignRight | Qt::AlignVCenter);
    layout()->setContentsMargins(10, 10, 10, 10);
    adjustSize(); // Adjust dialog size to fit contents
    setFixedSize(size());
}

void GroundwaterDialog::loadUiData(const GroundwaterDialogModel& data)
{
    m_includeWaterTableCheckbox->setChecked(data.includeWaterCheck);

    m_constantRadioButton->setChecked(data.constantRadioCheck);
    m_waterElevationLabel->setText(data.waterElevationLabelText);
    m_waterElevationLineEdit->setText(data.waterElevationValue);

    m_differentialRadioButton->setChecked(data.differentialRadioCheck);
    m_backslopeWaterElevationLabel->setText(data.backslopeWaterElevationLabelText);
    m_backslopeWaterElevationLineEdit->setText(data.backslopeWaterElevationValue);
    m_frontFaceWaterElevationLabel->setText(data.frontFaceWaterElevationLabelText);
    m_frontFaceWaterElevationLineEdit->setText(data.frontFaceWaterElevationValue);

    if (m_isMSE) {
        m_infiltratesReinforcedZoneCheckbox->setChecked(data.infiltratesReinforcedZoneCheck);
    }
    m_applyToAllSectionsCheckbox->setChecked(data.applyToAllSectionsCheck);
}

void GroundwaterDialog::saveUiData()
{
    m_currentData.includeWaterCheck = m_includeWaterTableCheckbox->isChecked();

    m_currentData.constantRadioCheck = m_constantRadioButton->isChecked();
    m_currentData.waterElevationLabelText = m_waterElevationLabel->text();
    m_currentData.waterElevationValue = m_waterElevationLineEdit->text();

    m_currentData.differentialRadioCheck = m_differentialRadioButton->isChecked();
    m_currentData.backslopeWaterElevationLabelText = m_backslopeWaterElevationLabel->text();
    m_currentData.backslopeWaterElevationValue = m_backslopeWaterElevationLineEdit->text();
    m_currentData.frontFaceWaterElevationLabelText = m_frontFaceWaterElevationLabel->text();
    m_currentData.frontFaceWaterElevationValue = m_frontFaceWaterElevationLineEdit->text();

    if (m_isMSE) {
        m_currentData.infiltratesReinforcedZoneCheck = m_infiltratesReinforcedZoneCheckbox->isChecked();
    }
    m_currentData.applyToAllSectionsCheck = m_applyToAllSectionsCheckbox->isChecked();
}
